public class NilR extends ObjectR{ 
    
    public ObjectR i;
    
    public void m(){
        i = new StringR("ads");
        ((StringR)i).test();
    }
    
    public IntegerR to_i() {
        return new IntegerR(0);
    }
    
    public ObjectR to_s() {
    
        return new StringR("nil");
    }

    //нужно для логических операций
    public int to_32int() {
        return 0;
    }
    
}
