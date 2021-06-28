package test.Model;
import main.Model.Users;
import org.junit.jupiter.api.Test;
import java.io.IOException;

/**
 * Class of test on Users
 */
class UsersTest {
    /**
     * Test of reading users
     * @throws IOException Exception to prevent IO errors
     */
    @Test
    void containsUser() throws IOException{
        Users users = new Users();
        users.readUsersFile("input_files/users_full.csv");
        assert users.containsUser("ak0TdVmGKo4pwqdJSTLwWw");
    }
}
