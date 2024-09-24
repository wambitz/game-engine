FROM ubuntu:22.04

# Set environment variables
ENV DEBIAN_FRONTEND=noninteractive

# Update and install required packages
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    git \
    cmake \
    sudo \
    curl \
    ca-certificates \
    clang-format \
    tree \
    gdb

# Clean up to keep the image size small
RUN apt clean && \
    rm -rf /var/lib/apt/lists/*

# Create a new user 'user' with sudo privileges
RUN useradd -m user && \
    echo "user ALL=(ALL) NOPASSWD: ALL" > /etc/sudoers.d/user && \
    chmod 0440 /etc/sudoers.d/user

# Use sed to uncomment the force_color_prompt line in ~/.bashrc
RUN sed -i 's/#force_color_prompt=yes/force_color_prompt=yes/g' /home/user/.bashrc

# Switch to the 'user' you created
USER user

# Default command
CMD ["/bin/bash"]
