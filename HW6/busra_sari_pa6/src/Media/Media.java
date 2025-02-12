package Media;

/**
 * The Media interface represents a generic media item.
 */
public interface Media {
    /**
     * Displays information about the media item.
     */
    void info();

    /**
     * Retrieves the name of the media item.
     *
     * @return the name of the media item
     */
    String getName();
}
