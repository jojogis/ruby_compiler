public class StringR extends ObjectR{ 
    
    public StringR(String str) {
        strValue = str;
    }
    
    public ObjectR to_s() {
        return this;
    }
    
    public IntegerR to_i() {
        try{
            return new IntegerR(Integer.parseInt(strValue));
        }
        catch (NumberFormatException ex){
            return new IntegerR(0);
        }
    }
    
    public StringR indexROP (ObjectR other) throws Exception{
        if (other instanceof IntegerR) {
            return new StringR(String.valueOf(strValue.charAt(other.intValue)));
        } else {
            throw new Exception("TypeError: no implicit conversion of "+other.getClass().getName() + " into integer");
        }
    }
    
    public StringR plusROP (ObjectR other) throws Exception{
        if (other instanceof StringR) {
            return new StringR(strValue + other.strValue);
        } else {
            throw new Exception("TypeError: no implicit conversion of "+other.getClass().getName() + " into String");
        }
    }
    
    public void test(){}

    //нужно для логических операций
    public int to_32int() {
        return 0;
    }
    
}
