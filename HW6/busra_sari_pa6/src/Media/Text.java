package Media;

/**
 * Represents a text media item that is non-visual and non-playable.
 */
public class Text implements Non_visual, Non_playable {
    private String name;
    private String info;

    /**
     * Constructs a Text object with the specified name and additional information.
     *
     * @param name the name of the text
     * @param info additional information about the text
     */
    public Text(String name, String info) {
        this.name = name;
        this.info = info;
    }

    /**
     * Displays information about the text.
     */
    @Override
    public void info() {
        System.out.println("Text: " + name + ", Info: " + info);
    }

    /**
     * Retrieves the name of the text.
     *
     * @return the name of the text
     */
    @Override
    public String getName() {
        return name;
    }
}

