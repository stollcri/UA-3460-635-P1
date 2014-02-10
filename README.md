# Image Segmentation Using Ford-Fulkerson
- Michael Crouse and Christopher Stoll
- Dr. Duan
- 635 Advanced Algorithms
- February 10, 2014

The objecive of this project was to use the Ford-Fullkerson network flow algorithm to solve an image segmentation problem. The use of breadth first search (BFS) was required to find paths from the source node to the sink node in the Ford-Fullkerson algorithm.

In order to apply a flow network to segmenting an image each pixel in the image was viewed as a vertex within a flow network. Each vertex was connected to adjecnt nodes by edges forming a von Neumann neighborhood of range 1. The capacity of the edges was determined by the difference in the pixels' z-dimensions. Since the images used in this project were grey-scale, the z-dimension was the 8-bit darkness of the pixel; a white pixel had a z value of 0 and a black pixel had a z value of 255.

For the purposes this project the goal of image segmentation was to seperate the background from the foreground of the greyscale image and either white-out or black-out the background of the image. 





According to the max-flow min-cut theorum, the maximum flow from the source to the sink of a flow network coresponds with the minimum cut required to stop the flow from the source to the sink.




To apply the Ford-Fulkerson algorithm to the image segmentation problem it will be viewed as a minimum cut problem. 


The Ford-Fulkerson algorithm can find the maximum flow of a flow network