import java.util.*;

public class CBRHistory
{
    static
    {
        System.loadLibrary("NativeCaller");
    }

    public static void main(String[] args)
    {
        String char_code = "USD";
        String start_date = "01.01.2017";
        String end_date = "01.02.2017";
        String file_name = "java_forex.xml";

        if (args.length >= 4)
        {
            char_code = args[0];
            start_date = args[1];
            end_date = args[2];
            file_name = args[3];  
        }

		NativeCaller caller = new NativeCaller();
        CurrencyDataContainer data = 
            caller.callHistory(char_code, start_date, end_date, file_name);

        for(Map.Entry<String, CurrencyData> el : data.get_all().entrySet())
        {
            System.out.println(el.getKey() + "/" + el.getValue());
        }
	}
}