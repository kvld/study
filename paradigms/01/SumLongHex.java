public class SumLongHex {

    public static void main(String[] args)
    {
        long sum = 0;
        for (int i = 0; i < args.length; i++) {
            String[] tmp = args[i].trim().split("\\p{javaWhitespace}");
            for (int j = 0; j < tmp.length; j++) {
                if (!tmp[j].isEmpty()) {
                    if (tmp[j].startsWith("0x") || tmp[j].startsWith("0X")) {
                            sum += Long.parseUnsignedLong(tmp[j].substring(2), 16);
                    } else {
                            sum += Long.parseLong(tmp[j], 10);
                    }
                }
            }
        }
        System.out.println(sum);
    }
}