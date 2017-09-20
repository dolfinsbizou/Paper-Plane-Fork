pipeline {
    agent any

    environment {
        BUILD_FILES = sh(
            // The fuck is this insanity? https://gist.github.com/Faheetah/e11bd0315c34ed32e681616e41279ef4
            script: 'find ./ -name \\"*.cpp\\" | tr \\"\\\\\\n\\" \\" \\"',
            returnStdout: true
        )
    }

    stages {
        stage('Build') {
            steps {
                echo "${ENV:BUILD_FILES}"
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
            echo "${ENV:BUILD_FILES}"
            //eclairsReport 'out/tuto', "${ENV:BUILD_FILES}", false, false, true, false, false, false
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
