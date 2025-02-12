package Observer;

import Media.Playable;
import Media.Visual;
import Media.Media;
import Media.Non_visual;

import java.util.ArrayList;
import java.util.List;

/**
 * The Player class implements the Observer interface and represents an observer
 * that plays playable media items such as audio and video.
 */
public class Player implements Observer {
    private static int playerCount = 1;
    private String name;

    private List<Playable> playList;
    private int currentIndex;

    /**
     * Constructs a new Player with a unique name and initializes the playlist.
     */
    public Player() {
        this.name = "Player" + playerCount++;
        playList = new ArrayList<>();
        currentIndex = -1;
    }

    /**
     * Returns the name of the player.
     *
     * @return the name of the player.
     */
    @Override
    public String getName() {
        return name;
    }

    /**
     * Displays the current playlist of the player.
     */
    @Override
    public void show_list() {
        System.out.print("\n");
        if (playList.isEmpty()) {
            System.out.println("[" + name + "] Playlist is empty.");
        } else {
            System.out.println("[" + name + "] Playlist:");
            for (Playable playable : playList) {
                playable.info();
            }
        }
    }

    /**
     * Updates the player with a new media item.
     *
     * @param media the media item to be added.
     */
    @Override
    public void update(Media media) {
        if (media instanceof Playable) {
            playList.add((Playable) media);
            System.out.println("[" + name + "] New playable item added to the playlist: " + media.getName());
            if (currentIndex == -1) {
                currentIndex = 0;
            }
        }
    }

    /**
     * Removes a media item from the player's playlist.
     *
     * @param media the media item to be removed.
     */
    @Override
    public void updateRemove(Media media) {
        if (media instanceof Playable) {
            playList.remove(media);
            System.out.println("[" + name + "] Playable item removed from the playlist: " + media.getName());
            if (currentIndex >= playList.size()) {
                currentIndex = playList.size() - 1;
            }
        }
    }

    /**
     * Adds multiple playable items to the playlist.
     *
     * @param playables the list of playable items to be added.
     */
    public void addPlayables(List<Playable> playables) {
        playList.addAll(playables);
        System.out.println("[" + name + "] New playable items added to the playlist.");
        if (currentIndex == -1 && !playList.isEmpty()) {
            currentIndex = 0;
        }
    }

    /**
     * Returns the currently playing item.
     *
     * @return the currently playing Playable item.
     */
    public Playable currently_playing() {
        System.out.print("\n");
        if (playList.isEmpty() || currentIndex == -1) {
            throw new IllegalStateException("No playable items in the playlist.");
        }
        Playable currentPlayable = playList.get(currentIndex);
        System.out.println("[" + name + "] Currently playing: " + currentPlayable.getName());
        return currentPlayable;
    }

    /**
     * Plays the next playable item of the specified type (audio or video).
     *
     * @param type the type of media item to play next ("audio" or "video").
     */
    public void next(String type) {
        if (playList.isEmpty()) {
            throw new IllegalStateException("No playable items in the playlist.");
        }
        try {
            for (int i = currentIndex + 1; i < playList.size(); i++) {
                if ((type.equals("audio") && playList.get(i) instanceof Non_visual) ||
                        (type.equals("video") && playList.get(i) instanceof Visual)) {
                    currentIndex = i;
                    playList.get(currentIndex).play();
                    return;
                }
            }
            throw new IllegalStateException("No next playable item of type " + type + " found.");
        } catch (IllegalStateException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }

    /**
     * Plays the previous playable item of the specified type (audio or video).
     *
     * @param type the type of media item to play previous ("audio" or "video").
     */
    public void previous(String type) {
        if (playList.isEmpty()) {
            throw new IllegalStateException("No playable items in the playlist.");
        }
        try {
            for (int i = currentIndex - 1; i >= 0; i--) {
                if ((type.equals("audio") && playList.get(i) instanceof Non_visual) ||
                        (type.equals("video") && playList.get(i) instanceof Visual)) {
                    currentIndex = i;
                    playList.get(currentIndex).play();
                    return;
                }
            }
            throw new IllegalStateException("No previous playable item of type " + type + " found.");
        } catch (IllegalStateException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}
