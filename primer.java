public class primer{
	public static void sololetra(String cadena){
		for(int i=0; i<cadena.length();i++){
			if ((cadena.charAt(i) >= 65 && cadena.charAt(i) <= 90) || (cadena.charAt(i) >= 97 && cadena.charAt(i) <= 122)){
				System.out.print(cadena.charAt(i)+" ");
			}
		}
	}
	public static void imprimir(int[] array){
		for(int val : array){
			System.out.print(val + " , ");
		}
	}
	//hacer fobonaci: bigInteger
	public static void main (String[] args){
	//	sololetra("a1b2cA4F7");
	//	int[] a = new int[]{5,4,3,2,1,0};
//		imprimir(a);
		Double real = new Double("12.423");
		Object obj = real;
		System.out.println(real);
		System.out.println(obj);
		//real = obj;
		Double nreal = (Double)obj;
		System.out.println(nreal);
		System.out.println(real);
	}
}