package Media;

/**
 * Represents an image media item that is visual and non-playable.
 */
public class Image implements Visual, Non_playable {
    private String name;
    private String dimensions;
    private String info;

    /**
     * Constructs an Image object with the specified name, dimensions, and additional information.
     *
     * @param name       the name of the image
     * @param dimensions the dimensions of the image
     * @param info       additional information about the image
     */
    public Image(String name, String dimensions, String info) {
        this.name = name;
        this.dimensions = dimensions;
        this.info = info;
    }

    /**
     * Displays information about the image.
     */
    @Override
    public void info() {
        System.out.println("Image: " + name + ", Dimensions: " + dimensions + ", Info: " + info);
    }

    /**
     * Shows the image.
     */
    @Override
    public void show() {
        System.out.println("Showing image: " + name);
    }

    /**
     * Retrieves the name of the image.
     *
     * @return the name of the image
     */
    @Override
    public String getName() {
        return name;
    }
}

