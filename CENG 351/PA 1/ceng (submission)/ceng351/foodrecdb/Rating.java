package ceng.ceng351.foodrecdb;

public class Rating {

    private int ratingID;
    private int itemID;
    private int rating;
    private String ratingDate;

    public Rating(int ratingID, int itemID, int rating, String ratingDate) {
        this.ratingID = ratingID;
        this.itemID = itemID;
        this.rating = rating;
        this.ratingDate = ratingDate;
    }

    public int getRatingID() {
        return ratingID;
    }

    public void setRatingID(int code) {
        this.ratingID = ratingID;
    }

    public int getItemID() {
        return itemID;
    }

    public void setItemID(int itemID) {
        this.itemID = itemID;
    }

    public int getRating() {
        return rating;
    }

    public void setRating(int rating) {
        this.rating = rating;
    }

    public String getRatingDate() {
        return ratingDate;
    }

    public void setRatingDate(String ratingDate) {
        this.ratingDate = ratingDate;
    }
    
    @Override
    public String toString() {
        return ratingID + "\t" + itemID + "\t" + rating + "\t" + ratingDate;
    }
    
}
