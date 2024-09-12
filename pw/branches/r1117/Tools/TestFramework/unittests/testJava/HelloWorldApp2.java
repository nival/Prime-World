import org.junit.* ;
import static org.junit.Assert.* ;

public class HelloWorldApp2 
{
    public static void main(String[] args) 
    {
        System.out.println("Hello World!");
    }

	@Test 
	public void simpleAdd() 
    {
		assertTrue(2+2==4);
    }
	@Test 
	public void simpleAdd2() 
    {
		assertTrue(3+2==5);
    }
    @Test
	public void simpleAdd3() 
    {
		assertFalse(3+2==4);
    }
}