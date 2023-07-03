package ceng.ceng351.foodrecdb;

public class QueryResult {

    public static class MenuItemAverageRatingResult{

        String itemID;
        String itemName;
        String avgRating;

        public MenuItemAverageRatingResult(
                String itemID,
                String itemName,
                String avgRating) {

            this.itemID = itemID;
            this.itemName = itemName;
            this.avgRating = avgRating;
        }

        public String toString() {
            return itemID + "\t" + itemName +"\t" + avgRating;
        }
    }

    public static class CuisineWithAverageResult{

        String cuisineName;
        String average;

        public CuisineWithAverageResult(
                String cuisineName,
                String average) {

            this.cuisineName = cuisineName;
            this.average = average;
        }

        public String toString() {
            return cuisineName + "\t" + average;
        }
    }

}
