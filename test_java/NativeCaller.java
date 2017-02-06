
class NativeCaller
{
    static
    {
        System.loadLibrary("libNativeCaller");
    }

    // обращаем внимание на слово native
    public native void callHistory(String char_code, 
                                   String start_date,
                                   String end_date,
                                   String file_name);
}