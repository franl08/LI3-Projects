package test.Model;
import main.Model.Business;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

/**
 * Class of tests on Business
 */
class BusinessTest {
    /**
     * Test of info getters on Business class
     */
    @Test
    void getInfo(){
        String expectedID = "12345";
        String expectedName = "SuperBusiness";
        String expectedCity = "Braga";
        String expectedState = "PT";
        String expectedCategories = "Everything";
        Business b = new Business(expectedID, expectedName, expectedCity, expectedState, expectedCategories);
        String actualID = b.getId();
        String actualName = b.getName();
        String actualCity = b.getCity();
        String actualState = b.getState();
        String actualCategories = b.getCategories();
        assertEquals(expectedID, actualID);
        assertEquals(expectedName, actualName);
        assertEquals(expectedCity, actualCity);
        assertEquals(expectedState, actualState);
        assertEquals(expectedCategories, actualCategories);
    }
}
