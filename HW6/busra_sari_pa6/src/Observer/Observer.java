package Observer;

import Media.Media;

/**
 * The Observer interface represents an observer in the observer pattern.
 */
public interface Observer {
    
    /**
     * Updates the observer with new media.
     *
     * @param media the new media to update the observer with.
     */
    void update(Media media);

    /**
     * Updates the observer upon removal of media.
     *
     * @param media the removed media.
     */
    void updateRemove(Media media);

    /**
     * Retrieves the name of the observer.
     *
     * @return the name of the observer.
     */
    String getName();

    /**
     * Prints the name of the observer.
     */
    default void printName() {
        System.out.println(getName());
    }

    /**
     * Displays the list of media being observed by the observer.
     */
    void show_list();

}
