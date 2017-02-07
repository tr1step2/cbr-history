import java.util.*;
import java.util.Collections.*;

public class CurrencyDataContainer
{
    CurrencyDataContainer()
    {
        m_data = new TreeMap<String, CurrencyData>();
    }

    public Map<String, CurrencyData> get_all()
    {
        return m_data;
    }

    public CurrencyData get(String date)
    {
        return m_data.get(date);
    }

    public void add(CurrencyData currencyData)
    {
        System.out.format("Get DATA {%s | %d | %f}\n", currencyData.date,
            currencyData.nominal, currencyData.value);

        m_data.put(currencyData.date, currencyData);
    }

    private Map<String, CurrencyData> m_data;
}