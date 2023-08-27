import datetime

from django.test import TestCase
from django.utils import timezone

from polls.models import Question


class QuestionModuleTests(TestCase):
    def test_was_published_recently_with_future_question(self):
        time = timezone.now() + datetime.timedelta(days=30)
        future_questions = Question(pub_date=time)
        self.assertFalse(future_questions.was_published_recently())

    def test_was_published_recently_with_old_question(self):
        time = timezone.now() - datetime.timedelta(days=1, seconds=1)
        old_questions = Question(pub_date=time)
        self.assertFalse(old_questions.was_published_recently())

    def test_was_published_recently_with_recent_question(self):
        time = timezone.now() - datetime.timedelta(hours=23, minutes=59, seconds=59)
        recent_questions = Question(pub_date=time)
        self.assertTrue(recent_questions.was_published_recently())
