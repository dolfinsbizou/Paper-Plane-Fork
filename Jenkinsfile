
FILES = sh(
    script: 'find ./ -name "*.cpp"',
    returnStdout: true
)

pipeline {
    agent any

    stages {
        stage('Build') {
            steps {
                //updateGitlabCommitStatus name: 'build', state: 'running'
                eclairsBuild()
            }
        }
        /*
        stage('Test') {
            steps {
                eclairsTest 'tests', 'out/tests', ''
            }
        }
        //*/
    }
    post {
        always {
            echo ${FILES}
            eclairsReport 'out/tuto', ${FILES}, false, false, true, false, false, false
            sh 'make clean'
        }
        /*
        aborted {
            updateGitlabCommitStatus name: 'build', state: 'canceled'
        }
        failure {
            updateGitlabCommitStatus name: 'build', state: 'failed'
        }
        unstable {
            eclairsArchive 'tuto'
            updateGitlabCommitStatus name: 'build', state: 'success'
        }
        //*/
        success {
            eclairsArchive 'tuto'
            //updateGitlabCommitStatus name: 'build', state: 'success'
        }
    }
    /*
    options {
        gitLabConnection('DRF gitlab')
    }
    triggers {
        gitlab(triggerOnPush: true, triggerOnMergeRequest: true, branchFilterType: 'All')
    }
    //*/
}
