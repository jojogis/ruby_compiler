public class BooleanR extends ObjectR{ 
    public BooleanR(boolean value) {
        boolValue = value;
    }
    public ObjectR to_s() {
        if (boolValue) {
            return new StringR("true");
        } else {
            return new StringR("false");        
        }
    }
    
    public int to_32int() {
        if(boolValue){
            return 1;
        }else{
            return 0;
        }
    }
    
}
