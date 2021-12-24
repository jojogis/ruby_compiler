import java.io.InputStreamReader;
import java.io.BufferedReader;

public class IO{

    public static ObjectR puts(ObjectR obj) {
        ObjectR b = obj;
        System.out.print(obj.to_s().strValue);
        System.out.print("\n");
        return new NilR();
    }
    
    public static ObjectR gets() {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        String result = null;
        try {
            result = reader.readLine();
        } catch (Exception e) {
            e.printStackTrace();
        }
        return new StringR(result);
    }

}

