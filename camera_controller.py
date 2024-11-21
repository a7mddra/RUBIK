import cv2


def correct_droidcam_feed(cap, width_scale=0.8, height_scale=1.0):
    """
    This function checks if the camera is using DroidCam and applies correction.

    Parameters:
    - cap: The video capture object (cv2.VideoCapture)
    - width_scale: The scale to adjust the width (default is 0.8 for DroidCam stretch)
    - height_scale: The scale to adjust the height (default is 1.0, no change)

    Returns:
    - Corrected width and height of the video capture feed.
    """

    frame_width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
    frame_height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))

    current_aspect_ratio = frame_width / frame_height

    if current_aspect_ratio > 1.5:
        print(f"Detected stretched feed, applying correction: {width_scale}x for width.")


        new_width = int(frame_width * width_scale)
        new_height = int(frame_height * height_scale)

        return new_width, new_height

    else:

        return frame_width, frame_height
