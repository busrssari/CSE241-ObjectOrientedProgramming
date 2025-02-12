package Media;

/**
 * Represents a video media item that is visual and playable.
 */
public class Video implements Visual, Playable {
    private String name;
    private String duration;
    private String info;

    /**
     * Constructs a Video object with the specified name, duration, and additional information.
     *
     * @param name     the name of the video
     * @param duration the duration of the video
     * @param info     additional information about the video
     */
    public Video(String name, String duration, String info) {
        this.name = name;
        this.duration = duration;
        this.info = info;
    }

    /**
     * Displays information about the video.
     */
    @Override
    public void info() {
        System.out.println("Image: " + name + ", Dimensions: " + duration + ", Info: " + info);
    }

    /**
     * Plays the video.
     */
    @Override
    public void play() {
        System.out.println("Showing video: " + name);
    }

    /**
     * Shows the video.
     */
    @Override
    public void show() {
        System.out.println("Showing video: " + name);
    }

    /**
     * Retrieves the name of the video.
     *
     * @return the name of the video
     */
    @Override
    public String getName() {
        return name;
    }
}

