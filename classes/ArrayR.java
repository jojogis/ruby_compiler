import java.util.ArrayList;

public class ArrayR extends ObjectR{ 
    
    public ArrayR() {
        arrayVal = new ArrayList<>();
    }
    
    public StringR to_s() {
        String result = "[";
        for (ObjectR obj: arrayVal){
            result += obj.to_s().strValue + ", ";
        }
        result = result.substring(0, result.length() - 2);
        result += "]";
        return new StringR(result);
    }
    
    public IntegerR to_i() throws Exception{
        throw new Exception("NoMethodError: undefined method `to_i' for Array");
    }
    
    public ObjectR pushROP (ObjectR other) throws Exception{
        arrayVal.add(other);
        return this;
    }
    
    public ObjectR indexROP (ObjectR other) throws Exception{
        if (other instanceof IntegerR) {
            return arrayVal.get(other.intValue);
        } else {
            throw new Exception("TypeError: no implicit conversion of "+other.getClass().getName() + " into integer");
        }
    }
    
    public ObjectR plusROP (ObjectR other) throws Exception{
        if (other instanceof ArrayR) {
            arrayVal.addAll(other.arrayVal);
            return this;
        } else {
            throw new Exception("TypeError: no implicit conversion of "+other.getClass().getName() + " into Array");
        }
    }
    
    public ObjectR minusROP (ObjectR other) throws Exception{
        if (other instanceof IntegerR) {
            return new IntegerR(intValue - other.intValue);
        } else if (other instanceof FloatR) {
            return new FloatR(intValue - other.floatValue);
        } else {
            throw new Exception(other.getClass().getName() + "can't be coerced into Integer");
        }
    }
    

    
    //нужно для логических операций
    public int to_32int() {
        if (arrayVal.size() > 0){
            return 1;
        } else {
            return 0;
        }
        
    }
    
} 
