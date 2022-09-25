import static java.lang.System.out;

public class Endianness {

  public static int bigEndianValue (Byte[] mem) {
    // TODO
    int bigEndian = 0;
    bigEndian+=mem[0]*1000000;
    bigEndian+=mem[1]*10000;
    bigEndian+=mem[2]*100;
    bigEndian+=mem[3];
    return bigEndian;
  }
  
  public static int littleEndianValue (Byte[] mem) {
    // TODO
    int littleEndian = 0;
    littleEndian+=mem[3]*1000000;
    littleEndian+=mem[2]*10000;
    littleEndian+=mem[1]*100;
    littleEndian+=mem[0];
    return littleEndian;
  }
  
  public static void main (String[] args) {
    Byte mem[] = new Byte[4];
    try {
      for (int i=0; i<4; i++)
        mem [i] = Integer.valueOf (args[i], 16) .byteValue();
    } catch (Exception e) {
      out.printf ("usage: java Endianness n0 n1 n2 n3\n");
      out.printf ("where: n0..n3 are byte values in memory at addresses 0..3 respectively, in hex (no 0x).\n");
      return;
    }
  
    int bi = bigEndianValue    (mem);
    int li = littleEndianValue (mem);
    
    out.printf ("Memory Contents\n");
    out.printf ("  Addr   Value\n");
    for (int i=0; i<4; i++)
      out.printf ("  %3d:   0x%-5x\n", i, mem[i]);
    out.printf ("The big    endian integer value at address 0 is %d\n", bi);
    out.printf ("The little endian integer value at address 0 is %d\n", li);
  }
}
