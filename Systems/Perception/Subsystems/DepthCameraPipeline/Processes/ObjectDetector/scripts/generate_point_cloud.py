import numpy as np

def generate_pcd(filename="test_cloud.pcd"):
    # 1. Configuration
    n_sphere = 300
    n_box = 400
    
    # 2. Object A: A Red Sphere
    sphere_center = np.array([0.4, 0.4, 1.0])
    r = 0.15
    theta = np.random.uniform(0, 2 * np.pi, n_sphere)
    phi = np.random.uniform(0, np.pi, n_sphere)
    
    x1 = sphere_center[0] + r * np.sin(phi) * np.cos(theta) + np.random.normal(0, 0.005, n_sphere)
    y1 = sphere_center[1] + r * np.sin(phi) * np.sin(theta) + np.random.normal(0, 0.005, n_sphere)
    z1 = sphere_center[2] + r * np.cos(phi) + np.random.normal(0, 0.005, n_sphere)
    
    # Pack Red color (R=255, G=0, B=0) into PCL bitwise float format
    rgb1 = np.full(n_sphere, (255 << 16) | (0 << 8) | 0, dtype=np.uint32)

    # 3. Object B: A Green Box
    box_center = np.array([-0.4, -0.4, 1.2])
    x2 = np.random.uniform(-0.1, 0.1, n_box) + box_center[0]
    y2 = np.random.uniform(-0.1, 0.1, n_box) + box_center[1]
    z2 = np.random.uniform(-0.1, 0.1, n_box) + box_center[2]
    
    # Pack Green color (R=0, G=255, B=0)
    rgb2 = np.full(n_box, (0 << 16) | (255 << 8) | 0, dtype=np.uint32)

    # Combine all points
    X = np.concatenate([x1, x2])
    Y = np.concatenate([y1, y2])
    Z = np.concatenate([z1, z2])
    RGB = np.concatenate([rgb1, rgb2])
    
    total_points = len(X)

    # 4. Write PCD Header & Data (ASCII Format)
    with open(filename, "w") as f:
        f.write("# .PCD v0.7 - Point Cloud Data generated for testing\n")
        f.write("VERSION 0.7\n")
        f.write("FIELDS x y z rgb\n")
        f.write("SIZE 4 4 4 4\n")
        f.write("TYPE F F F U\n")  # Float, Float, Float, Unsigned Integer for RGB
        f.write("COUNT 1 1 1 1\n")
        f.write(f"WIDTH {total_points}\n")
        f.write("HEIGHT 1\n")
        f.write("VIEWPOINT 0 0 0 1 0 0 0\n")
        f.write(f"POINTS {total_points}\n")
        f.write("DATA ascii\n")
        
        # Write coordinates and color bits
        for i in range(total_points):
            f.write(f"{X[i]:.4f} {Y[i]:.4f} {Z[i]:.4f} {RGB[i]}\n")
            
    print(f"[Success] Generated '{filename}' with {total_points} points.")

if __name__ == "__main__":
    generate_pcd()
