public class FloatR extends ObjectR implements ComparableR{
    
    public FloatR(float num) {
        floatValue = num;
    }
    
    public StringR to_s() {
        return new StringR(String.valueOf(floatValue));
    }
    
    public IntegerR to_i() {
        return new IntegerR((int)floatValue);
    }
    
    public FloatR plusROP (ObjectR other) throws Exception{
        if (other instanceof IntegerR) {
            return new FloatR(floatValue + other.intValue);
        } else if (other instanceof FloatR) {
            return new FloatR(floatValue + other.floatValue);
        } else {
            throw new Exception(other.getClass().getName() + "can't be coerced into Float");
        }
    }
    
    public FloatR minusROP (ObjectR other) throws Exception{
        if (other instanceof IntegerR) {
            return new FloatR(floatValue - other.intValue);
        } else if (other instanceof FloatR) {
            return new FloatR(floatValue - other.floatValue);
        } else {
            throw new Exception(other.getClass().getName() + "can't be coerced into Float");
        }
    }
    
    public FloatR multROP (ObjectR other) throws Exception{
        if (other instanceof IntegerR) {
            return new FloatR(floatValue * other.intValue);
        } else if (other instanceof FloatR) {
            return new FloatR(floatValue * other.floatValue);
        } else {
            throw new Exception(other.getClass().getName() + "can't be coerced into Float");
        }
    }
    
    public FloatR divROP (ObjectR other) throws Exception{
        if (other instanceof IntegerR) {
            return new FloatR(floatValue / other.intValue);
        } else if (other instanceof FloatR) {
            return new FloatR(floatValue / other.floatValue);
        } else {
            throw new Exception(other.getClass().getName() + "can't be coerced into Float");
        }
    }
    
    public ObjectR LtROP(ObjectR other) throws Exception{
        if (other instanceof IntegerR) {
            return new BooleanR(floatValue < other.intValue);
        } else if (other instanceof FloatR) {
            return new BooleanR(floatValue < other.floatValue);
        } else {
            throw new Exception("comparison of Float with " + other.getClass().getName() + " failed");
        }
    }
    
    public ObjectR GtROP(ObjectR other) throws Exception{
        if (other instanceof IntegerR) {
            return new BooleanR(floatValue > other.intValue);
        } else if (other instanceof FloatR) {
            return new BooleanR(floatValue > other.floatValue);
        } else {
            throw new Exception("comparison of Float with " + other.getClass().getName() + " failed");
        }
    }
    
    public ObjectR LeROP(ObjectR other) throws Exception{
        if (other instanceof IntegerR) {
            return new BooleanR(floatValue <= other.intValue);
        } else if (other instanceof FloatR) {
            return new BooleanR(floatValue <= other.floatValue);
        } else {
            throw new Exception("comparison of Float with " + other.getClass().getName() + " failed");
        }
    }
    
    public ObjectR GeROP(ObjectR other) throws Exception {
        if (other instanceof IntegerR) {
            return new BooleanR(floatValue >= other.intValue);
        } else if (other instanceof FloatR) {
            return new BooleanR(floatValue >= other.floatValue);
        } else {
            throw new Exception("comparison of Float with " + other.getClass().getName() + " failed");
        }
    }
    
    public ObjectR EqROP(ObjectR other) throws Exception {
        if (other instanceof IntegerR) {
            return new BooleanR(floatValue == other.intValue);
        } else if (other instanceof FloatR) {
            return new BooleanR(floatValue == other.floatValue);
        } else {
            throw new Exception("comparison of Float with " + other.getClass().getName() + " failed");
        }
    }
    
    //нужно для логических операций
    public int to_32int() {
        return 1;
    }
} 
