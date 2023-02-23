package ceng.ceng351.foodrecdb;

public class DietaryCategory {
    
    private int ingredientID;
    private String dietaryCategory;

    public DietaryCategory(int ingredientID, String dietaryCategory) {
        this.ingredientID = ingredientID;
        this.dietaryCategory = dietaryCategory;
    }

    public int getIngredientID() {
        return ingredientID;
    }

    public void setIngredientID(int ingredientID) {
        this.ingredientID = ingredientID;
    }

    public String getDietaryCategory() {
        return dietaryCategory;
    }

    public void setDietaryCategory(String dietaryCategory) {
        this.dietaryCategory = dietaryCategory;
    }

    @Override
    public String toString() {
        return ingredientID + "\t" + dietaryCategory;
    }
}
