package main.Model;

import java.util.List;
import java.util.Map;
import java.util.Set;

/**
 * Reviews Interface
 */
public interface ReviewsInterface {

    /**
     * Method to get number of reviews
     * @return Number of reviews
     */
    int getNumberOfReviews();

    /**
     * Method to check if the catalog contains a review given its ID
     * @param ID ID to check
     * @return true if it exists, false otherwise
     */
    boolean existsReview(String ID);

    /**
     * Method to add a review to reviews catalog
     * @param r Review to add
     */
    void addReview(ReviewInterface r);

    /**
     * Cloner method
     * @return Cloned catalog
     */
    ReviewsInterface clone();

    /**
     * Method to get number of businesses reviewed
     * @return Number of businesses reviewed
     */
    int getNumberOfBusinessesReviewed();

    /**
     * Method to get Set of businesses IDs with reviews
     * @return Set of businesses IDs with reviews
     */
    Set<String> businessesReviewed();

    /**
     * Method to get number of users with reviews
     * @return Number of users with reviews
     */
    int getNumberOfUsersWithReviews();

    /**
     * Method to get number of reviews without impact
     * @return Number of reviews without impact
     */
    int getNumberOfReviewsWithoutImpact();

    /**
     * Method to get a Map associating months with number of reviews of that month
     * @return Map associating months with number of reviews of that month
     */
    Map<Integer, Integer> getNumberOfReviewsPerMonth();

    /**
     * Method to get reviews average grade
     * @return Reviews average grade
     */
    Float getGlobalAverage();

    /**
     * Method to get a Map associating months with the average grade of that month
     * @return Map associating months with the average grade of that month
     */
    Map<Integer, Float> getAveragePerMonth();

    /**
     * Method to get a Map associating months with the number of distinct users who made reviews in that month
     * @return Map associating months with the number of distinct users who made reviews in that month
     */
    Map<Integer, Integer> getDifferentUsersPerMonth();

    /**
     * Auxiliary method to get query 2
     * @param month Month
     * @param year Year
     * @return Query 2 answer
     */
    Query2Pair query2(int month, int year);

    /**
     * Auxiliary method to get query 3
     * @param user User ID
     * @return Query 3 answer
     */
    Map<Integer, Query3Triple> query3(String user);

    /**
     * Auxiliary method to get query 4
     * @param businessID Business ID
     * @return Query 4 answer
     */
    Map<Integer, Query4Triple> query4(String businessID);

    /**
     * Auxiliary method to get query 5
     * @param userID User ID
     * @param idsAndNames Map associating businesses IDs with businesses names
     * @return Query 5 answer
     */
    List<Map.Entry<String, Integer>> query5(String userID, Map<String, String> idsAndNames);

    /**
     * Auxiliary method to get query 6
     * @param lim Number of asked parameters
     * @return Query 6 answer
     */
    Map<Integer, List<Map.Entry<String, Long>>> query6(int lim);

    /**
     * Auxiliary method to get query 7
     * @param businessesByCity Map associating cities with businesses IDs of each city
     * @return Query 7 answer
     */
    Map<String, List<String>> query7(Map<String, Set<String>> businessesByCity);

    /**
     * Auxiliary method to get query 8
     * @param limit Number of asked parameters
     * @return Query 8 answer
     */
    List<Map.Entry<String, Long>> query8(int limit);

    /**
     * Auxiliary method to get query 9
     * @param businessID Business ID
     * @param limit Number of asked parameters
     * @return Query 9 answer
     */
    List<Map.Entry<String, Float>> query9(String businessID, int limit);

    /**
     * Auxiliary method to get query 10
     * @param m Map associating Businesses States with a Map associating Sets of Businesses IDs with their cities
     * @return Query 10 answer
     */
    Map<String, Map<String, Map<String, Float>>> query10(Map<String, Map<String, Set<String>>> m);
}
