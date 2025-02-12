package Observer;

import Media.*;
import java.util.ArrayList;
import java.util.List;

/**
 * The Dataset class represents a collection of media items and manages
 * observers
 * to notify them about changes in the dataset.
 */
public class Dataset {
    private List<Media> mediaList;
    private List<Observer> observers;

    /**
     * Constructs a new Dataset with empty media list and observer list.
     */
    public Dataset() {
        mediaList = new ArrayList<>();
        observers = new ArrayList<>();
    }

    /**
     * Adds a new media item to the dataset and notifies observers.
     *
     * @param media the media item to be added.
     */
    public void add(Media media) {
        System.out.print("\n");
        mediaList.add(media);
        System.out.println("Media added to the dataset: " + media.getName());
        notifyObservers(media);
    }

    /**
     * Removes a media item from the dataset and notifies observers.
     *
     * @param media the media item to be removed.
     */
    public void remove(Media media) {
        System.out.print("\n");
        if (mediaList.remove(media)) {
            System.out.println("Media removed from the dataset: " + media.getName());
            notifyObserversRemove(media);
        }
    }

    /**
     * Removes a media item from the dataset by its name and notifies observers.
     *
     * @param mediaName the name of the media item to be removed.
     */
    public void remove(String mediaName) {
        for (Media media : mediaList) {
            if (media.getName().equals(mediaName)) {
                mediaList.remove(media);
                System.out.println("Media removed from the dataset: " + mediaName);
                notifyObserversRemove(media);
                return;
            }
        }
        System.out.println("Media with name " + mediaName + " not found.");
    }

    /**
     * Displays the list of registered observers.
     */
    public void showObserverList() {
        if (observers.isEmpty()) {
            System.out.println("Observer list is empty.");
        } else {
            System.out.println("Observer List:");
            for (Observer observer : observers) {
                System.out.println(observer.getName());
            }
        }
    }

    /**
     * Registers an observer to receive updates from the dataset.
     *
     * @param observer the observer to be registered.
     */
    public void register(Observer observer) {
        observers.add(observer);
        System.out.println("Observer registered: " + observer.getName());
    }

    /**
     * Removes an observer from receiving updates from the dataset.
     *
     * @param observer the observer to be removed.
     */
    public void remove_observer(Observer observer) {
        observers.remove(observer);
        System.out.println("Observer removed: " + observer.getName());
    }

    /**
     * Notifies all observers about the addition of a new media item.
     *
     * @param media the media item that was added.
     */
    private void notifyObservers(Media media) {
        for (Observer observer : observers) {
            observer.update(media);
        }
    }

    /**
     * Notifies all observers about the removal of a media item.
     *
     * @param media the media item that was removed.
     */
    private void notifyObserversRemove(Media media) {
        for (Observer observer : observers) {
            observer.updateRemove(media);
        }
    }

    /**
     * Retrieves all playable media items from the dataset.
     *
     * @return a list of playable media items.
     */
    public List<Playable> getPlayables() {
        List<Playable> playables = new ArrayList<>();
        for (Media media : mediaList) {
            if (media instanceof Playable) {
                playables.add((Playable) media);
            }
        }
        return playables;
    }

    /**
     * Retrieves all non-playable media items from the dataset.
     *
     * @return a list of non-playable media items.
     */
    public List<Non_playable> getNonPlayables() {
        List<Non_playable> nonPlayables = new ArrayList<>();
        for (Media media : mediaList) {
            if (media instanceof Non_playable) {
                nonPlayables.add((Non_playable) media);
            }
        }
        return nonPlayables;
    }

    /**
     * Displays the list of media items in the dataset.
     */
    public void showMediaList() {
        if (mediaList.isEmpty()) {
            System.out.println("Media list is empty.");
        } else {
            System.out.println("Media List:");
            for (Media media : mediaList) {
                media.info();
            }
        }
    }
}
