package arch.sm213.machine.student;

import machine.AbstractMainMemory;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

public class MainMemoryTest {
    MainMemory memory;
    @BeforeEach
    public void setup(){
        memory = new MainMemory(4);
    }

    @Test
    public void isAccessAlignedTest() {
        // Testing the correct alignment when all the values before address [0..1999] are 4 bit data
        assertTrue(memory.isAccessAligned(2000,4));

        // Testing the wrong alignment when NOT all the values before the address [0..126] are 8-bit data
        assertFalse(memory.isAccessAligned(127, 8));
    }

    @Test
    public void bytesToIntegerTest() {
        // Testing positive number 0x1 0x1 0x1 0x1 has 0 as a most significant bit, so the output should be positive
        assertEquals(memory.bytesToInteger((byte)1,(byte)1,(byte)1,(byte)1),16843009);

        // For the negative case, 0xff 0xff 0xff 0xff starts with 1 as a most significant bit, so the output should be negative
        assertEquals(memory.bytesToInteger((byte)255,(byte)255,(byte)255,(byte)255),-1);
    }

    @Test
    public void integerToBytesTest() {
        byte[] firstTestBytes = new byte[]{(byte) 0, (byte) 0, (byte) 0, (byte) 100};
        byte[] secondTestBytes = new byte[]{(byte)255, (byte)255, (byte)255, (byte)227};
        // Test the positive case, when the most significant bit is 0, hence the value is positive
        assertArrayEquals(memory.integerToBytes(100), firstTestBytes);

        // Test the negative case, when the most significant bit is 1, hence the value is also negative
        assertArrayEquals(memory.integerToBytes(-29), secondTestBytes);
    }

    @Test
    public void getTest() throws AbstractMainMemory.InvalidAddressException {
        /*
            getTest method tests both get and set methods of MainMemory,
            because standalone set method does not output values which can be tested
         */
        // Testing the edge case, when the value we want to set and get is the first member of an array
        // before test: mem = [0, 0, 0, 0]
        // after test: mem = [128, 0, 0, 0]
        byte[] firstTest = new byte[]{(byte)128};
        memory.set(0, firstTest);
        assertArrayEquals(memory.get(0,1), firstTest);

        // Testing another edge case, when we set and get a value from address to length-1 [address..mem.length-1]
        // before test: [128, 0, 0, 0]
        // after test: [128, 0, 5, 5]
        byte[] secondTest = new byte[]{(byte)5, (byte) 5};
        memory.set(2, secondTest);
        assertArrayEquals(memory.get(2,2), secondTest);

        // Testing the regular case, when the set and get values does not lie on the edge values of the array
        // before test: [128, 0, 5, 5]
        // after test: [128, 12, 34, 5]
        byte[] thirdTest = new byte[]{(byte)12, (byte) 34};
        memory.set(1, thirdTest);
        assertArrayEquals(memory.get(1,2), thirdTest);

    }

}
