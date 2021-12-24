import java.util.ArrayList;
import java.lang.reflect.*;
 
public class ObjectR {

    public ObjectR test;

    public float floatValue;

    public int intValue;
    
    public boolean boolValue;
    
    public ArrayList<ObjectR> arrayVal;
    
    public String strValue;
    
    public ObjectR call(ObjectR name, ObjectR ... args) throws Exception{//, 
        ArrayList<Class<?>> arr = new ArrayList<Class<?>>();
        
        for(int i = 0; i < args.length; i++){
            arr.add(ObjectR.class);
        }
        
        Method method = getClass().getMethod(name.to_s().strValue, arr.toArray(new Class<?>[0]));
        return (ObjectR)method.invoke(this, (Object[])args);
    }
    
    public void test() throws Exception{
    
        call(new ObjectR(), new ObjectR());
    }
    public IntegerR to_i() throws Exception{
        throw new Exception("NoMethodError: undefined method `to_i' for " + getClass().getName());
    }
    
    public StringR class_name () {
        return new StringR(getClass().getName());
    }
    public ObjectR to_s () {
        return new StringR("");
    }
    
    public ObjectR plusROP (ObjectR other) throws Exception{
        throw new Exception("NoMethodError: undefined method `+' for " + getClass().getName());
    }
    
    public ObjectR minusROP (ObjectR other) throws Exception{
        throw new Exception("NoMethodError: undefined method `-' for " + getClass().getName());
    }
    
    public ObjectR multROP (ObjectR other) throws Exception{
        throw new Exception("NoMethodError: undefined method `*' for " + getClass().getName());
    }
    
    public ObjectR divROP (ObjectR other) throws Exception{
        throw new Exception("NoMethodError: undefined method `/' for " + getClass().getName());
    }
    
    public ObjectR indexROP (ObjectR other) throws Exception{
        throw new Exception("NoMethodError: undefined method `[]' for " + getClass().getName());
    }
    
    public ObjectR pushROP (ObjectR other) throws Exception{
        throw new Exception("NoMethodError: undefined method `<<' for " + getClass().getName());
    }
    
    public ObjectR eqlROP (ObjectR other) {
        return new BooleanR(this == other);//TODO сравнение для всех объектов
    }
    
    
    //нужно для логических операций
    public int to_32int() {
        return 0;
    }
}
