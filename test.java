import java.math.BigInteger;
public class test {
	public static byte[] get (int address, int length) throws Exception {
		    // TODO
		if (!isAccessAligned(address,length))
			throw new Exception();
		else {
			byte[] output = new byte[length];
			byte[] value = integerToBytes(address);
			for (int i = 0; i < length; i++){
				output[i] = value[i];
			}
			return output;
		}
	}
	public static byte[] integerToBytes (int i) {
		// TODO
		return new byte[] {
			(byte)(i >>> 24),
			(byte)(i >>> 16),
			(byte)(i >>> 8),
			(byte)i};                                                           }
	public static boolean isAccessAligned (int address, int length) {
		// TODO
		byte[] bytes = integerToBytes(address);
		int byteLength = 0;
		for (byte b: bytes){
			if (b != 0) {
				byteLength++;
				System.out.format("0x%x ", b);
			}
		}
		return byteLength == length;
	}	
	public static void main(String[] args) throws Exception{
		int value = Integer.valueOf(args[0]);
		int leng = Integer.valueOf(args[1]);
		
//		System.out.println("method test");
//		System.out.println(isAccessAligned(value, leng));
		System.out.println(get(value,leng).length);
	}
}
