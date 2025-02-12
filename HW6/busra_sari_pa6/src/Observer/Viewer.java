package Observer;

import Media.Media;
import Media.Non_playable;
import Media.Visual;
import Media.Non_visual;

import java.util.ArrayList;
import java.util.List;

/**
 * The Viewer class implements the Observer interface and represents an observer 
 * that views non-playable media items. It maintains a list of non-playable media 
 * items and allows navigating through them.
 */
public class Viewer implements Observer {
    private static int viewerCount = 1;
    private String name;
    private List<Non_playable> viewList;
    private int currentIndex;

    /**
     * Constructs a new Viewer with a unique name.
     */
    public Viewer() {
        this.name = "Viewer" + viewerCount++;
        viewList = new ArrayList<>();
        currentIndex = -1;
    }

    /**
     * Returns the name of the viewer.
     * 
     * @return the name of the viewer.
     */
    @Override
    public String getName() {
        return name;
    }

    /**
     * Displays the list of non-playable items being viewed by this viewer.
     */
    @Override
    public void show_list() {
        System.out.print("\n");
        if (viewList.isEmpty()) {
            System.out.println("[" + name + "] View list is empty.");
        } else {
            System.out.println("[" + name + "] View List:");
            for (Non_playable nonPlayable : viewList) {
                nonPlayable.info();
            }
        }
    }

    /**
     * Updates the viewer with a new media item. If the media is non-playable,
     * it is added to the view list.
     * 
     * @param media the new media item to be added.
     */
    @Override
    public void update(Media media) {
        if (media instanceof Non_playable) {
            viewList.add((Non_playable) media);
            System.out.println("[" + name + "] New non-playable item added to the view list: " + media.getName());
            if (currentIndex == -1) {
                currentIndex = 0;
            }
        }
    }

    /**
     * Updates the viewer by removing a media item. If the media is non-playable,
     * it is removed from the view list.
     * 
     * @param media the media item to be removed.
     */
    @Override
    public void updateRemove(Media media) {
        viewList.remove(media);
        System.out.println("[" + name + "] Non-playable item removed from the view list: " + media.getName());
        if (currentIndex >= viewList.size()) {
            currentIndex = viewList.size() - 1;
        }
    }

    /**
     * Returns the currently viewed non-playable item.
     * 
     * @return the currently viewed non-playable item.
     * @throws IllegalStateException if there are no non-playable items in the view list.
     */
    public Non_playable currently_viewing() {
        System.out.print("\n");
        if (viewList.isEmpty() || currentIndex == -1) {
            throw new IllegalStateException("No non-playable items in the view list.");
        }
        Non_playable currentNonPlayable = viewList.get(currentIndex);
        System.out.println("[" + name + "] Currently viewing: " + currentNonPlayable.getName());
        return currentNonPlayable;
    }

    /**
     * Adds a list of non-playable items to the view list.
     * 
     * @param nonPlayables the list of non-playable items to be added.
     */
    public void addNonPlayables(List<Non_playable> nonPlayables) {
        viewList.addAll(nonPlayables);
        System.out.println("[" + name + "] New non-playable items added to the view list.");
        if (currentIndex == -1 && !viewList.isEmpty()) {
            currentIndex = 0;
        }
    }

    /**
     * Moves to the next non-playable item of the specified type and displays its info.
     * 
     * @param type the type of the next non-playable item ("text" or "image").
     */
    public void next(String type) {
        if (viewList.isEmpty()) {
            throw new IllegalStateException("No non-playable items in the view list.");
        }
        try {
            for (int i = currentIndex + 1; i < viewList.size(); i++) {
                if ((type.equals("text") && viewList.get(i) instanceof Non_visual) ||
                        (type.equals("image") && viewList.get(i) instanceof Visual)) {
                    currentIndex = i;
                    viewList.get(currentIndex).info();
                    return;
                }
            }
            throw new IllegalStateException("No next non-playable item of type " + type + " found.");
        } catch (IllegalStateException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }

    /**
     * Moves to the previous non-playable item of the specified type and displays its info.
     * 
     * @param type the type of the previous non-playable item ("text" or "image").
     */
    public void previous(String type) {
        if (viewList.isEmpty()) {
            throw new IllegalStateException("No non-playable items in the view list.");
        }
        try {
            for (int i = currentIndex - 1; i >= 0; i--) {
                if ((type.equals("text") && viewList.get(i) instanceof Non_visual) ||
                        (type.equals("image") && viewList.get(i) instanceof Visual)) {
                    currentIndex = i;
                    viewList.get(currentIndex).info();
                    return;
                }
            }
            throw new IllegalStateException("No previous non-playable item of type " + type + " found.");
        } catch (IllegalStateException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}
