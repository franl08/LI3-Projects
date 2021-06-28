package main.Model;

/**
 * Auxiliary Class to create Query 2 pair
 */
public class Query2Pair {
    /**
     * Number of total reviews
     */
    int totalReviews;
    /**
     * Number of different users
     */
    int differentUsers;

    /**
     * Parametrized Constructor
     * @param totalReviews Number of total reviews
     * @param differentUsers Number of different users
     */
    public Query2Pair(int totalReviews, int differentUsers){
        this.totalReviews = totalReviews;
        this.differentUsers = differentUsers;
    }

    /**
     * Total Reviews getter
     * @return Number of total reviews
     */
    public int getTotalReviews(){
        return this.totalReviews;
    }

    /**
     * Different users getter
     * @return Number of different users
     */
    public int getDifferentUsers(){
        return  this.differentUsers;
    }

    /**
     * Method to get pair as a String
     * @return Pair as a String
     */
    public String toString()
    {
        StringBuilder sb = new StringBuilder();

        sb.append("\nTotal reviews = ");
        sb.append(this.totalReviews);
        sb.append("\nDifferent users = ");
        sb.append(this.differentUsers);

        return sb.toString();
    }
}
