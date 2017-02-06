import java.util.*;


public class CBRHistory
{
    public static void main(String[] args)
    {
        String forex = "forex.xml";

/*        String char_code = args[0];
        String start_date = args[1];
        String end_date = args[2];
        String file_name = "java_forex.xml";
*/
		NativeCaller caller = new NativeCaller();
        caller.callHistory("USD", "01.01.2016", "01.01.2017", "forex_java_out.xml");
	}
}