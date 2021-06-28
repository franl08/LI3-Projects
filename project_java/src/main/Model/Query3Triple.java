package main.Model;

/**
 * Auxiliary Class to create Query 3 triple
 */
public class Query3Triple {
    /**
     * Number of reviews
     */
    int numberReviews;
    /**
     * Number of distinct businesses
     */
    int differentBusiness;
    /**
     * Average grade
     */
    float averageGrade;

    /**
     * Parametrized Constructor
     * @param numberReviews Number of reviews
     * @param differentBusiness Number of distinct users
     * @param averageGrade Average grade
     */
    public Query3Triple(int numberReviews, int differentBusiness, float averageGrade){
        this.numberReviews = numberReviews;
        this.differentBusiness = differentBusiness;
        this.averageGrade = averageGrade;
    }

    /**
     * Number of reviews getter
     * @return Number of reviews
     */
    public int getNumberReviews() {
        return this.numberReviews;
    }

    /**
     * Number of different businesses getter
     * @return Number of different businesses
     */
    public int getDifferentBusiness() {
        return this.differentBusiness;
    }

    /**
     * Average grade getter
     * @return Average grade
     */
    public float getAverageGrade() {
        return this.averageGrade;
    }

    /**
     * Method to get triple as a String
     * @return Triple as a String
     */
    public String toString()
    {
        StringBuilder sb = new StringBuilder();

        sb.append("\nNumber of reviews = ");
        sb.append(this.numberReviews);
        sb.append("\nDifferent businesses = ");
        sb.append(this.differentBusiness);
        sb.append("\nAverage grade = ");
        sb.append(this.averageGrade);

        return sb.toString();
    }
}
