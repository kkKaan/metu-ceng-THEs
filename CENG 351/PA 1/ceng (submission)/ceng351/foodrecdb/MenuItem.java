package ceng.ceng351.foodrecdb;

public class MenuItem {
    
    private int itemID;
    private String itemName;
    private String cuisine;
    private int price;

    public MenuItem(int itemID, String name, String cuisine, int price) {
        this.itemID = itemID;
        this.itemName = name;
        this.cuisine = cuisine;
        this.price = price;
    }

    public int getItemID() {
        return itemID;
    }

    public void setItemID(int itemID) {
        this.itemID = itemID;
    }

    public String getItemName() {
        return itemName;
    }

    public void setItemName(String name) {
        this.itemName = name;
    }

    public String getCuisine() {
        return cuisine;
    }

    public void setCuisine(String cuisine) {
        this.cuisine = cuisine;
    }

    public int getPrice() {
        return price;
    }

    public void setPrice(int price) {
        this.price = price;
    }

    
    @Override
    public String toString() {
        return itemID + "\t" + itemName + "\t" + cuisine + "\t" + price;
    }
    
    
}
