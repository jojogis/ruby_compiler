public class NilR extends ObjectR{ 
    
    public IntegerR to_i() {
        return new IntegerR(0);
    }

    //нужно для логических операций
    public int to_32int() {
        return 0;
    }
    
}
