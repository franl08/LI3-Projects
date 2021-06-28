package test.Model;

import main.Model.Review;
import main.Model.Reviews;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;
import java.time.LocalDateTime;

/**
 * Class of tests on Reviews
 */
public class ReviewsTest {
    /**
     * Test of adding and getting reviews to catalog
     */
    @Test
    void getNumberOfReviews(){
        Reviews reviews = new Reviews();
        Review r = new Review("lWC-xP3rd6obsecCYsGZRg", "ak0TdVmGKo4pwqdJSTLwWw", "buF9druCkbuXLX526sGELQ", 4.0F, 3, 1, 1, LocalDateTime.of(2014, 10, 11, 3, 34, 2), "Text");
        Review useless = new Review("lWC-xJ3rd6obsecZYsGZRg", "aL0TdVmGKo4pwqdJSTLwWw", "buF9druCkbYXLX526sGELQ", 4.0F, 0, 0, 0, LocalDateTime.of(2014, 10, 11, 3, 34, 2), "Text");
        reviews.addReview(r);
        reviews.addReview(useless);
        assertEquals(reviews.getNumberOfReviews(), 2);
        assertEquals(reviews.getNumberOfReviewsWithoutImpact(), 1);
        assertEquals(reviews.getGlobalAverage(), 4.0F);
    }
}
