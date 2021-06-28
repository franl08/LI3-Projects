package main.Model;

import java.time.LocalDateTime;

/**
 * Review Interface
 */
public interface ReviewInterface {
    /**
     * Review ID getter
     * @return Review ID
     */
    String getReview_ID();

    /**
     * User ID getter
     * @return User ID
     */
    String getUser_ID();

    /**
     * Business ID getter
     * @return Business ID
     */
    String getBusiness_ID();

    /**
     * Stars getter
     * @return Stars
     */
    float getStars();

    /**
     * Useful getter
     * @return Useful
     */
    int getUseful();

    /**
     * Funny Getter
     * @return Funny
     */
    int getFunny();

    /**
     * Cool getter
     * @return Cool
     */
    int getCool();

    /**
     * Review cloner
     * @return Cloned review
     */
    Review clone();

    /**
     * Mont Number getter
     * @return Month Number
     */
    Integer getMonthNumber();

    /**
     * Date getter
     * @return Date
     */
    LocalDateTime getDate();

    /**
     * Text getter
     * @return Text
     */
    String getText();

    /**
     * Method to validate an ID
     * @param ID ID to check
     * @return true if ID is valid, false otherwise
     */
    static boolean verifyID(String ID){
        return ID.length() == 22;
    }
}
