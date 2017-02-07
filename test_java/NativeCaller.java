
class NativeCaller
{
    static
    {
        System.loadLibrary("NativeCaller");
    }

    // обращаем внимание на слово native
    public native void callHistory(String char_code, 
                                   String start_date,
                                   String end_date,
                                   String file_name);
}