import java.math.*;

public class Circulo extends Figura{
	private double radio;
	public Circulo(int x,int y, int rad) {
		super(x,y);
		this.radio = rad;
	}
	public double area() {
		return Math.PI * this.radio * this.radio;
	}
	public String toString() {
		String a = super.toString();
		return (a + ", de tipo circulo con radio:"+this.radio);
	}
}
