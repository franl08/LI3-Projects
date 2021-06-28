package test.Model;
import main.Model.Review;
import org.junit.jupiter.api.Test;

import java.time.LocalDateTime;

import static org.junit.jupiter.api.Assertions.*;

/**
 * Class of test on Review
 */
class ReviewTest {
    /**
     * Test of getting info of a Review
     */
    @Test
    void getInfo(){
        String rIdExpected = "lWC-xP3rd6obsecCYsGZRg";
        String uIdExpected = "ak0TdVmGKo4pwqdJSTLwWw";
        String bIdExpected = "buF9druCkbuXLX526sGELQ";
        float stExpected = 4.0F;
        int usExpected = 3;
        int funnyExpected = 1;
        int coolExpected = 1;
        LocalDateTime expectedLd = LocalDateTime.of(2014, 10, 11, 3, 34, 2);
        String expectedText = "Apparently Prides Osteria had a rough summer as evidenced by the almost empty dining room at 6:30 on a Friday night. However new blood in the kitchen seems to have revitalized the food from other customers recent visits. Waitstaff was warm but unobtrusive. By 8 pm or so when we left the bar was full and the dining room was much more lively than it had been. Perhaps Beverly residents prefer a later seating. After reading the mixed reviews of late I was a little tentative over our choice but luckily there was nothing to worry about in the food department. We started with the fried dough, burrata and prosciutto which were all lovely. Then although they don't offer half portions of pasta we each ordered the entree size and split them. We chose the tagliatelle bolognese and a four cheese filled pasta in a creamy sauce with bacon, asparagus and grana frita. Both were very good. We split a secondi which was the special Berkshire pork secreto, which was described as a pork skirt steak with garlic potato purée and romanesco broccoli (incorrectly described as a romanesco sauce). Some tables received bread before the meal but for some reason we did not. Management also seems capable for when the tenants in the apartment above began playing basketball she intervened and also comped the tables a dessert. We ordered the apple dumpling with gelato and it was also quite tasty. Portions are not huge which I particularly like because I prefer to order courses. If you are someone who orders just a meal you may leave hungry depending on you appetite. Dining room was mostly younger crowd while the bar was definitely the over 40 set. Would recommend that the naysayers return to see the improvement although I personally don't know the former glory to be able to compare. Easy access to downtown Salem without the crowds on this month of October.";
        Review r = new Review(rIdExpected, uIdExpected, bIdExpected, stExpected, usExpected, funnyExpected, coolExpected, expectedLd, expectedText);
        assertEquals(rIdExpected, r.getReview_ID());
        assertEquals(uIdExpected, r.getUser_ID());
        assertEquals(bIdExpected, r.getBusiness_ID());
        assertEquals(stExpected, r.getStars());
        assertEquals(usExpected, r.getUseful());
        assertEquals(funnyExpected, r.getFunny());
        assertEquals(coolExpected, r.getCool());
        assertEquals(expectedLd, r.getDate());
        assertEquals(expectedText, r.getText());
    }
}
