package test.Model;
import main.Model.Businesses;
import org.junit.jupiter.api.Test;

import java.io.IOException;

import static org.junit.jupiter.api.Assertions.*;

/**
 * Class of Tests on Businesses
 */
class BusinessesTest {
    /**
     * Test of reading businesses
     * @throws IOException Exception to prevent IO errors
     */
    @Test
    void containsBusiness() throws IOException{
        Businesses b = new Businesses();
        b.readBusinessesFile("input_files/business_full.csv");
        assert b.containsBusiness("tCbdrRPZA0oiIYSmHG3J0w");
    }
}
