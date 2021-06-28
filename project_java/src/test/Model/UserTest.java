package test.Model;

import main.Model.User;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

/**
 * Class of test on User
 */
class UserTest {
    /**
     * Test of getting info of an User
     */
    @Test
    void getInfo(){
        String expectedID = "User1";
        String expectedName = "MyName";
        User u = new User(expectedID, expectedName);
        String actualId = u.getId();
        String actualName = u.getName();
        assertEquals(expectedID, actualId);
        assertEquals(expectedName, actualName);
    }
}
