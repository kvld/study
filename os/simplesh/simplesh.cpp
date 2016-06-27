#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <sys/types.h>
#include <sys/uio.h>
#include <cstdio>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>

#define ERROR_CHECK(x) if ((x) == -1) {       \
    perror(#x); \
    exit(1); \
  }


using namespace std;

const int MAX_BUFFER = 4096;

vector<int> used_pids;

int handled_signal = -1;

void sig_handler(int sig) {
    handled_signal = sig;
}

void remove_died(vector<int>& pids) {
    for (auto it = pids.begin(); it != pids.end(); ) {
        if (kill(*it, 0) == 0) {
            it = pids.erase(it);
        } else {
            it++;
        }
    }
}

char buffer[MAX_BUFFER];

int main () {
    struct sigaction sa;
    sa.sa_handler = &sig_handler;
    sa.sa_flags = 0;
                     
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGINT);
    sigaddset(&sa.sa_mask, SIGCHLD);

    if (sigaction(SIGINT, &sa, NULL) != 0) {
        perror("error in sigaction");
        return -1;
    }

    if (sigaction(SIGCHLD, &sa, NULL) != 0) {
        perror("error in sigaction");
        return -1;
    }

    string input;
    while (true) {
        write(STDOUT_FILENO, "$ ", 2);

        bool new_line = false;
        while (!new_line && input.find('\n') == string::npos) {
            ssize_t read_cnt = read(STDIN_FILENO, buffer, MAX_BUFFER);

            // Ctrl+D
            if (read_cnt == 0) {
                write(STDOUT_FILENO, "\n", 1);
                exit(0);
            }

            for (int i = 0; i < read_cnt; i++) {
                input += buffer[i];
                new_line = new_line || (buffer[i] == '\n');
            }
        }

        size_t pos = input.find('\n');

        string command = input.substr(0, pos);
        input.erase(0, pos + 1);

        int *pipefd = new int[2];
        pipe(pipefd);

        bool is_pipe_closed = false;

        int *cur_pipefd = pipefd;

        used_pids.clear();

        size_t delimeter_pos = 0;
        int i = 0;

        while (true) {
            if (delimeter_pos == string::npos || command == "") {
                break;
            }

            delimeter_pos = command.find('|');
            string part;
            if (delimeter_pos == string::npos) {
                part = command.substr(0, command.length());
            } else {
                part = command.substr(0, delimeter_pos);
            }

            command = delimeter_pos == string::npos ? "" : command.substr(delimeter_pos + 1);

            int begin = part.find_first_not_of(" ");
            int end = part.find_last_not_of(" \n");
            int range = end - begin + 1;

            part = part.substr(begin, range);
            size_t first_space = part.find(" ");

            string cur_command;
            if (first_space == string::npos) {
                cur_command = part.substr(0, part.length());
            } else {
                cur_command = part.substr(0, first_space);
            }
            string args = first_space == string::npos ? "" : part.substr(first_space + 1, part.length());

            // "uname      -a" -> "uname -a"
            vector<string> splitted_args;
            args += " ";
            splitted_args.push_back(cur_command);
            string cur_arg = "";
            for (int i = 0; i < args.length(); i++) {
                if (args[i] == ' ') {
                    if (cur_arg != "") {
                        splitted_args.push_back(cur_arg);
                        cur_arg = "";
                    }
                } else {
                    cur_arg += args[i];
                }
            }
            vector<char*> splitted_args_c;
            for (int i = 0; i < splitted_args.size(); i++) {
                splitted_args_c.push_back((char*)splitted_args[i].c_str());
            }
            splitted_args_c.push_back(NULL);

            handled_signal = 0;

            int *pipe_s = new int[2];
            pipe(pipe_s);

            int *pipe_f = cur_pipefd;
            cur_pipefd = pipe_s;

            bool is_first_command = i == 0;
            bool is_last_command = delimeter_pos == string::npos;
            pid_t pid = fork();
            if (pid == 0) {
                ERROR_CHECK(dup2(pipe_f[0], STDIN_FILENO));
                if (!is_last_command) {
                    ERROR_CHECK(dup2(pipe_s[1], STDOUT_FILENO));
                }
                ERROR_CHECK(close(pipe_f[0]));
                ERROR_CHECK(close(pipe_f[1]));

                ERROR_CHECK(close(pipe_s[0]));
                ERROR_CHECK(close(pipe_s[1]));

                int ret_code = execvp(cur_command.c_str(), &splitted_args_c[0]);
                if (ret_code == -1) {
                    cout << "Command not found." << endl;
                }
                exit(0);
            } else {
                if (!is_first_command) {
                    ERROR_CHECK(close(pipe_f[0]));
                    ERROR_CHECK(close(pipe_f[1]));
                }
                used_pids.push_back(pid);
                handled_signal = 0;
            }

            i++;
        }

        while (used_pids.size() > 0) {
            ssize_t write_cnt = write(pipefd[1], input.c_str(), input.size());
            input.erase(0, write_cnt);

            ssize_t read_cnt = read(STDIN_FILENO, buffer, MAX_BUFFER);

            if (read_cnt != -1) {
                for (int i = 0; i < read_cnt; i++) input += buffer[i];
            }

            if (read_cnt == 0) {
                ERROR_CHECK(close(pipefd[1]));
                is_pipe_closed = true;
            }

            remove_died(used_pids);
            if (handled_signal == SIGINT) { 
                break;
            }
        }

        int temp;
        while (wait(&temp) > 0) { } 

        if (handled_signal == SIGINT) {
            for (int i = 0; i < used_pids.size(); i++) {
                kill(used_pids[i], SIGINT);
            }
        }

        if (!is_pipe_closed) {
            ERROR_CHECK(close(pipefd[1]));
        }

        ssize_t read_cnt;
        while ((read_cnt = read(pipefd[0], buffer, MAX_BUFFER)) > 0) {
            for (int i = 0; i < read_cnt; i++) input += buffer[i];
        }

        ERROR_CHECK(close(pipefd[0]));

        if (sigaction(SIGINT, &sa, NULL) != 0) {
            perror("error in sigaction");
            return -1;
        }

        if (sigaction(SIGCHLD, &sa, NULL) != 0) {
            perror("error in sigaction");
            return -1;
        }
    }

    return 0;
}