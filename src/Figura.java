
abstract class Figura {
//	protected int x;
//	protected int y;
	protected Coordenada coordenada;
	private final class Coordenada {
		private int x;
		private int y;
		public Coordenada(int x, int y) {
			this.x = x;
			this.y = y;
		}
		public int getX() {
			return x;
		}
		public int getY() {
			return y;
		}
	}
	
	public Figura() {
//		this(0,0);
		this.coordenada = new Coordenada(0,0);
	}
	public Figura(int x, int y) {
//		this.x=x;
//		this.y=y;
		this.coordenada = new Coordenada(x,y);
	}
	abstract double area();
	public String toString() {
		return "Esta es una figura en ["+(this.coordenada).getX() +","+ (this.coordenada).getY()+"]";
	}
}
