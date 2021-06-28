package main.Model;

import java.io.Serializable;
import java.time.LocalDateTime;

/**
 * Review Class
 */
public class Review implements ReviewInterface, Serializable {
    /**
     * Review ID
     */
    private final String review_ID;
    /**
     * User ID
     */
    private final String user_ID;
    /**
     * Business ID
     */
    private final String business_ID;
    /**
     * Stars
     */
    private final float stars;
    /**
     * Useful
     */
    private final int useful;
    /**
     * Funny
     */
    private final int funny;
    /**
     * Cool
     */
    private final int cool;
    /**
     * Date
     */
    private final LocalDateTime date;
    /**
     * Text
     */
    private final String text;

    /**
     * Parametrized Constructor
     * @param review_ID Review ID
     * @param user_ID User ID
     * @param business_ID Business ID
     * @param stars Stars
     * @param useful Useful
     * @param funny Funny
     * @param cool Cool
     * @param date Date
     * @param text Text
     */
    public Review(String review_ID, String user_ID, String business_ID, float stars, int useful, int funny, int cool, LocalDateTime date, String text){
        this.review_ID = review_ID;
        this.user_ID = user_ID;
        this.business_ID = business_ID;
        this.stars = stars;
        this.useful = useful;
        this.funny = funny;
        this.cool = cool;
        this.date = date;
        this.text = text;
    }

    /**
     * Copy Constructor
     * @param r Review to copy
     */
    public Review(Review r){
        this.review_ID = r.getReview_ID();
        this.user_ID = r.getUser_ID();
        this.business_ID = r.getBusiness_ID();
        this.stars = r.getStars();
        this.useful = r.getUseful();
        this.funny = r.getFunny();
        this.cool = r.getCool();
        this.date = r.getDate();
        this.text = r.getText();
    }

    /**
     * Review cloner
     * @return Cloned review
     */
    public Review clone(){
        return new Review(this);
    }

    /**
     * Review ID getter
     * @return Review ID
     */
    public String getReview_ID() {
        return this.review_ID;
    }

    /**
     * User ID getter
     * @return User ID
     */
    public String getUser_ID() {
        return this.user_ID;
    }

    /**
     * Business ID getter
     * @return Business ID
     */
    public String getBusiness_ID() {
        return this.business_ID;
    }

    /**
     * Stars getter
     * @return Stars
     */
    public float getStars() {
        return this.stars;
    }

    /**
     * Useful getter
     * @return Useful
     */
    public int getUseful() {
        return this.useful;
    }

    /**
     * Funny Getter
     * @return Funny
     */
    public int getFunny() {
        return this.funny;
    }

    /**
     * Cool getter
     * @return Cool
     */
    public int getCool() {
        return this.cool;
    }

    /**
     * Date getter
     * @return Date
     */
    public LocalDateTime getDate() {
        return this.date;
    }

    /**
     * Text getter
     * @return Text
     */
    public String getText() {
        return this.text;
    }

    /**
     * Mont Number getter
     * @return Month Number
     */
    public Integer getMonthNumber(){
        return this.date.getMonthValue();
    }

}
