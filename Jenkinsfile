pipeline {
  agent {
    docker {
      image 'cpp'
    }

  }
  stages {
    stage('Build') {
      steps {
        sh 'cmake'
      }
    }
  }
}