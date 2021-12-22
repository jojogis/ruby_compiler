public class IntegerR extends ObjectR implements ComparableR{ 
    
    public IntegerR(int num) {
        intValue = num;
    }
    
    public StringR to_s() {
        return new StringR(String.valueOf(intValue));
    }
    
    public IntegerR to_i() {
        return this;
    }
    
    public ObjectR plusROP (ObjectR other) throws Exception{
        if (other instanceof IntegerR) {
            return new IntegerR(intValue + other.intValue);
        } else if (other instanceof FloatR) {
            return new FloatR(intValue + other.floatValue);
        } else {
            throw new Exception(other.getClass().getName() + " can't be coerced into Integer");
        }
    }
    
    public ObjectR minusROP (ObjectR other) throws Exception{
        if (other instanceof IntegerR) {
            return new IntegerR(intValue - other.intValue);
        } else if (other instanceof FloatR) {
            return new FloatR(intValue - other.floatValue);
        } else {
            throw new Exception(other.getClass().getName() + " can't be coerced into Integer");
        }
    }
    
    public ObjectR multROP (ObjectR other) throws Exception{
        if (other instanceof IntegerR) {
            return new IntegerR(intValue * other.intValue);
        } else if (other instanceof FloatR) {
            return new FloatR(intValue * other.floatValue);
        } else {
            throw new Exception(other.getClass().getName() + " can't be coerced into Integer");
        }
    }
    
    public ObjectR divROP (ObjectR other) throws Exception{
        if (other instanceof IntegerR) {
            return new FloatR(intValue / other.intValue);
        } else if (other instanceof FloatR) {
            return new FloatR(intValue / other.floatValue);
        } else {
            throw new Exception(other.getClass().getName() + " can't be coerced into Integer");
        }
    }
    
    public ObjectR LtROP(ObjectR other) throws Exception{
        if (other instanceof IntegerR) {
            return new BooleanR(intValue < other.intValue);
        } else if (other instanceof FloatR) {
            return new BooleanR(intValue < other.floatValue);
        } else {
            throw new Exception("comparison of Integer with " + other.getClass().getName() + " failed");
        }
    }
    
    public ObjectR GtROP(ObjectR other) throws Exception{
        if (other instanceof IntegerR) {
            return new BooleanR(intValue > other.intValue);
        } else if (other instanceof FloatR) {
            return new BooleanR(intValue > other.floatValue);
        } else {
            throw new Exception("comparison of Integer with " + other.getClass().getName() + " failed");
        }
    }
    
    public ObjectR LeROP(ObjectR other) throws Exception{
        if (other instanceof IntegerR) {
            return new BooleanR(intValue <= other.intValue);
        } else if (other instanceof FloatR) {
            return new BooleanR(intValue <= other.floatValue);
        } else {
            throw new Exception("comparison of Integer with " + other.getClass().getName() + " failed");
        }
    }
    
    public ObjectR GeROP(ObjectR other) throws Exception {
        if (other instanceof IntegerR) {
            return new BooleanR(intValue >= other.intValue);
        } else if (other instanceof FloatR) {
            return new BooleanR(intValue >= other.floatValue);
        } else {
            throw new Exception("comparison of Integer with " + other.getClass().getName() + " failed");
        }
    }
    
    public ObjectR EqROP(ObjectR other) throws Exception {
        if (other instanceof IntegerR) {
            return new BooleanR(intValue == other.intValue);
        } else if (other instanceof FloatR) {
            return new BooleanR(intValue == other.floatValue);
        } else {
            throw new Exception("comparison of Integer with " + other.getClass().getName() + " failed");
        }
    }
    
    //нужно для логических операций
    public int to_32int() {
        return 1;// Число всегда true
    }
    
} 
