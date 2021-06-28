package main.Model;

/**
 * Auxiliary Class to get Query 4 triple
 */
public class Query4Triple {
    /**
     * Number of Reviews
     */
    int nReviews;
    /**
     * Number of Distinct Users
     */
    int distinctUsers;
    /**
     * Average
     */
    float average;

    /**
     * Parametrized Constructor
     * @param nReviews Number of Reviews
     * @param distinctUsers Number of Distinct Users
     * @param average Average
     */
    public Query4Triple(int nReviews, int distinctUsers, float average){
        this.nReviews = nReviews;
        this.distinctUsers = distinctUsers;
        this.average = average;
    }

    /**
     * Number of reviews getter
     * @return Number of reviews
     */
    public int getnReviews() {
        return this.nReviews;
    }

    /**
     * Number of distinct users getter
     * @return Number of distinct users
     */
    public int getDistinctUsers() {
        return this.distinctUsers;
    }

    /**
     * Average getter
     * @return Average
     */
    public float getAverage() {
        return this.average;
    }

    /**
     * Method to get triple as a String
     * @return Triple as a String
     */
    public String toString()
    {
        StringBuilder sb = new StringBuilder();

        sb.append("\nNumber of reviews = ");
        sb.append(this.nReviews);
        sb.append("\nDistinct users = ");
        sb.append(this.distinctUsers);
        sb.append("\nAverage = ");
        sb.append(this.average);

        return sb.toString();
    }
}
