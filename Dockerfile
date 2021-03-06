FROM fedora:25


RUN dnf update -y && dnf install openssh* wget bzip2 unzip git gcc-c++ java-1.8.0-openjdk java-1.8.0-openjdk-devel -y

# prepare ssh service here
RUN ssh-keygen -A
RUN mkdir /var/run/sshd

# use password 'youjumpijump' here
RUN echo 'root:youjumpijump' | chpasswd
# RUN sed -i 's/PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config


# SSH login fix. Otherwise user is kicked off after login
RUN sed 's@session\s*required\s*pam_loginuid.so@session optional pam_loginuid.so@g' -i /etc/pam.d/sshd

ENV NOTVISIBLE "in users profile"
RUN echo "export VISIBLE=now" >> /etc/profile
RUN echo "export JAVA_HOME=/usr/lib/jvm/java" >> /etc/profile

#
ADD . /app

# add bazel
RUN wget https://github.com/bazelbuild/bazel/releases/download/0.4.5/bazel-0.4.5-installer-linux-x86_64.sh -O bazel.sh && chmod +x bazel.sh && ./bazel.sh && rm -rf bazel.sh

RUN ln -sf /usr/local/lib/bazel/bin/bazel-complete.bash /etc/bash_completion.d/

# add miniconda
RUN wget https://repo.continuum.io/miniconda/Miniconda3-latest-Linux-x86_64.sh -O miniconda.sh && chmod +x miniconda.sh && ./miniconda.sh -b -p /usr/mc && rm -rf miniconda.sh
ENV PATH /usr/mc/bin:$PATH
RUN echo 'export PATH=/usr/mc/bin:$PATH' >> /etc/profile
RUN conda install --yes numpy

# setup
ENV DOCKER_FRONTEND "noninteractive"
RUN cd /app && ./setup && bazel build //...


# expose 22, and start sshd in default
EXPOSE 22
CMD ["/usr/sbin/sshd", "-D"]


