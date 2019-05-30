
class Cuadrado extends Figura{
	private int lado;
	public Cuadrado (int x, int y, int lado) {
		super(x,y);
		this.lado = lado;
	}
	public double area () {
		return this.lado * this.lado;
	}
	public String toString() {
		String a = super.toString();
		return (a + ", de tipo cuadrado con lado:"+this.lado);
	}
}
