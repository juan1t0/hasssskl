
public class Main {
	public static void main(String[] args) {
		Object circulo = new Circulo(1,1,100);
		Object cuadrado = new Cuadrado(2,2,10);
		
//		System.out.println(circulo);
//		System.out.println(cuadrado);
		System.out.println("o:" + ((Circulo)circulo).area());
		System.out.println("[]:" + ((Cuadrado)cuadrado).area());
		System.out.println("o:" + ((Circulo)circulo).toString());
		System.out.println("[]:" + ((Cuadrado)cuadrado).toString());
	}
}
